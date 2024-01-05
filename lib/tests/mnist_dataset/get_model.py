from torchvision import models
import csv

# Load a pre-trained CNN model
model = models.resnet18(pretrained=True)

# Save the model architecture to a .dat file
with open('model.dat', 'w') as file:
    file.write(str(model))

# Extract weights and biases from the model
params = []
for name, param in model.named_parameters():
    params.append({'name': name, 'data': param.data.numpy()})

# Save weights and biases to a .csv file
csv_file = 'weights_biases.csv'
with open(csv_file, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Name', 'Shape', 'Data'])
    for param in params:
        writer.writerow([param['name'], param['data'].shape, param['data']])
